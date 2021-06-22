import pymongo

myClient = pymongo.MongoClient(
    "mongodb+srv://respiraWorks:S5u7t5yOmomK0x9j@cluster0.7yqbv.mongodb.net/sampleData?retryWrites=true&w=majority"
)

myDB = myClient["sampleData"]
myColl = myDB["dataFiles"]


def testInsertion():
    arrOfData = [{"name": "John", "address": "Highway 37"}]
    insertData("sampleData123", "example/examples", arrOfData)


def createObjectToInsertToMongo(filename, filepath, dataToAdd):
    return {"filename": filename, "filepath": filepath, "data": dataToAdd}


def insertData(filename, filepath, dataToAdd):
    objectToAdd = createObjectToInsertToMongo(filename, filepath, dataToAdd)
    newDataPiece = myColl.insert_one(objectToAdd)
    print(newDataPiece)
