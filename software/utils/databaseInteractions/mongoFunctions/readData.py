import pymongo

myClient = pymongo.MongoClient(
    "mongodb+srv://respiraWorks:S5u7t5yOmomK0x9j@cluster0.7yqbv.mongodb.net/sampleData?retryWrites=true&w=majority"
)

myDB = myClient["sampleData"]
myColl = myDB["dataFiles"]


def testGetData():
    testData = myColl.find_one()
    print(testData)


def getFileData(filename):
    fileData = myColl.find_one({"filename": filename})
    return fileData
