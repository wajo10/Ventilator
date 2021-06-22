import os.path
import json
from bson import json_util  # this will convert object ids with MongoDB!
from mongoFunctions.readData import getFileData


def downloadFile(filename):
    data = getFileData(filename)
    stringOfData = json.dumps(data, default=json_util.default)

    savePath = "downloadedDataFiles/"
    if not os.path.isdir(savePath):
        os.mkdir(savePath)

    completeName = os.path.join(savePath + filename.split(".")[0] + ".txt")

    # f = open(filename.split(".")[0] + ".txt", "w")
    # print(completeName)
    f = open(completeName + ".txt", "w")

    f.write(stringOfData)
    f.close()


downloadFile("gui-sample-data.dat")
