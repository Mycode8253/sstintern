import sst

obj = sst.Component("mycpu", "mcpu.InternoCpu")
obj.addParams({
    "printFrequency" : "5",
    "repeats" : "5"
    })

