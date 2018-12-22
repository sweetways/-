//index.js
//获取应用实例
const app = getApp()

Page({
  tapName: function() {
    var that = this
    //从oneNET请求我们的Wi-Fi气象站的数据
    const requestTask = wx.request({
      url: 'https://api.heclouds.com/devices/503948909/datapoints?datastream_id=do,re,mi,so,la&limit=1',
      header: {
        'content-type': 'application/json',
        'api-key': 'pP7sowvkaUypZyLn=CnNimSfdXA='
      },
      success: function (res) {
        that.setData({
          a: res.data.data.datastreams["2"].datapoints["0"].value,
          b: res.data.data.datastreams["0"].datapoints["0"].value,
          c: res.data.data.datastreams["3"].datapoints["0"].value,
          d: res.data.data.datastreams["4"].datapoints["0"].value,
          e: res.data.data.datastreams["1"].datapoints["0"].value,

        });

        console.log(res);
        console.log(that.data);  //打印返回的数据
      },

      fail: function (res) {
        console.log("fail!!!")
      },

      complete: function (res) {
        console.log("end")
      }
    })
  },


  data: {
    a: '',
   b: '',
    c: '',
   d: '',
    e: '',
  },

  onLoad: function () {
    var that = this
    //从oneNET请求我们的Wi-Fi气象站的数据
    const requestTask = wx.request({
      url: 'https://api.heclouds.com/devices/503948909/datapoints?datastream_id=do,re,mi,so,la&limit=1',
      header: {
        'content-type': 'application/json',
        'api-key':'pP7sowvkaUypZyLn=CnNimSfdXA='
      },
      success: function (res) {
        that.setData({
          a: res.data.data.datastreams["2"].datapoints["0"].value,
          b: res.data.data.datastreams["0"].datapoints["0"].value,
          c: res.data.data.datastreams["3"].datapoints["0"].value,
          d: res.data.data.datastreams["4"].datapoints["0"].value,
          e: res.data.data.datastreams["1"].datapoints["0"].value,

        });

        console.log(res)   ; 
        console.log(that.data);  //打印返回的数据
      },

      fail: function (res) {
        console.log("fail!!!")
      },

      complete: function (res) {
        console.log("end")
      }
    })
  },

})
