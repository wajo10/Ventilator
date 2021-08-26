# NOW SETUP MONGO FUNCTIONALITY
import pymongo
import json
from mongoFunctions.readData import testGetData
from mongoFunctions.insertData import testInsertion, insertData
from mongoFunctions.deleteData import deleteAllCollectionData

myClient = pymongo.MongoClient(
    "mongodb+srv://respiraWorks:S5u7t5yOmomK0x9j@cluster0.7yqbv.mongodb.net/sampleData?retryWrites=true&w=majority"
)

myDB = myClient["sampleData"]
myColl = myDB["oldDataFiles"]
metaDataFileName = "meta-data.json"
# testInsertion()
deleteAllCollectionData(
    "dataFiles"
)  # this will delete the entire database to do a fresh upload, this could be disabled, and we could run a check to only upload new files!

# NOW LET'S LOOP THROUGH OUR FILES AND CREATE DATA IN MONGO
##
##
def grabAllHeadersAndGetDataStart(fileLines):
    count = 0

    for line in fileLines:
        # print(line)
        count += 1

        if line and line[0] != "#" and line[0] != " ":
            headers = line.split()
            return (count, headers)


def createDataToInsert(fileLines, startOfData, headers):
    dataToPutIntoMongo = []
    for line in fileLines[startOfData:]:
        # print(line)

        data = {}
        dataPoint = line.split()

        cnt = 0
        for col in headers:
            data[col] = dataPoint[cnt]
            cnt = cnt + 1

        dataToPutIntoMongo.append(data)

    return dataToPutIntoMongo


def uploadFile(mypath, filename):
    f = open(mypath + filename, "r")  # changed from mypath + "/" filename
    # print(f.read())
    # print(filename)

    fileLines = [x.strip() for x in f]
    tupleResults = grabAllHeadersAndGetDataStart(
        fileLines
    )  # let's grab this files headers!

    countStartOfData = tupleResults[0]
    headers = tupleResults[1]

    # print(headers)

    dataToSave = createDataToInsert(fileLines, countStartOfData, headers)
    savedPath = mypath.split("..")[2] + filename
    # insertData("gui-sample-data.dat", dataToSave)

    # grab metadata to add to the database
    metaData = (
        json.load(open(mypath + metaDataFileName, "r"))
        if os.path.isfile(mypath + metaDataFileName)
        else None
    )
    metaDataSpecificToThisTest = (
        json.load(open(mypath + (filename.split(".")[0] + "-" + metaDataFileName), "r"))
        if os.path.isfile(mypath + (filename.split(".")[0] + "-" + metaDataFileName))
        else None
    )

    insertData(filename, savedPath, dataToSave, metaData, metaDataSpecificToThisTest)


# NOW GRAB ALL FILENAMES
##
##
import os

current_dir = os.path.dirname(os.path.realpath(__file__))
print(current_dir)

from os import listdir
from os.path import isfile, isdir, join

mypath = current_dir + "/../../sample-data/"  # + "2020-07-31-UFlow-Performance/"
# print(mypath)


def getAllFilesInDir(path):
    return [f for f in listdir(path) if isfile(join(path, f))]


def getAllDirsInDir(path):
    return [d for d in listdir(path) if isdir(join(path, d))]


def grabAllDataFiles(onlyfiles):
    outputOfFileNames = []

    for file in onlyfiles:
        if ".dat" in file:
            outputOfFileNames.append(file)

    return outputOfFileNames


def loopThroughFilesAndUpload(mypath, arrOfFiles):
    for file in arrOfFiles:
        uploadFile(mypath, file)


def downloadAllFiles(tmppath, level, onlyUploadBaseDirectory):

    # recursively loop through directories to find all data files! -- this feature can be disabled easily
    if not onlyUploadBaseDirectory:
        onlydir = getAllDirsInDir(tmppath)
        for dirName in onlydir:
            filePath = tmppath + dirName + "/"
            downloadAllFiles(filePath, level + 1, False)

    # get the file names and download them -- can uncomment to test a specific directory
    # if (tmppath == "/Users/brennankolotinsky/Documents/RespiraWorks/Ventilator/software/utils/databaseInteractions/../../sample-data/2020-06-16-covent-tests/"):
    onlyfiles = getAllFilesInDir(tmppath)
    dataFiles = grabAllDataFiles(onlyfiles)
    loopThroughFilesAndUpload(tmppath, dataFiles)


# uploadFile(mypath, "gui-sample-data.dat")  # upload a specific example
downloadAllFiles(mypath, 0, False)  # switch to false!
