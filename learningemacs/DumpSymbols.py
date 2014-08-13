import pymongo
import datetime

client = pymongo.MongoClient("192.168.1.101", 27017)
db = client.gccf

def testfunction(s):
    #this is a test of emacs
    


if __name__ == "__main__":
    query = {}
    startdate = datetime.datetime(2012, 8, 3)
    enddate = datetime.datetime(2012, 8, 4)
    # filter to add some date time
    query["$and"] = [{"dt" : {"$gt" : startdate}} , {"dt" : {"$lt" : enddate}}]
    # filter to select specific stock
    query["s"] = "PX"
    # filter to select trades
    query["v"] = {"$gt" : 0}
    # filter to select quotes
    #query["b"] = {"$gt": 0 }
    cursor = db.taq.find(query, {"_id" : 0}).sort("dt", 1).limit(20)
    for c in cursor:
        print str(c["dt"]) + "," + \
              c["s"] + "," + \
              c["ex"] + "," + \
              str(c["b"]) + "," + \
              str(c["a"]) + "," + \
              str(c["bz"]) + "," + \
              str(c["az"]) + "," + \
              str(c["pr"]) + "," + \
              str(c["v"])


