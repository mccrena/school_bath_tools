// pages/index/index.js
Page({
  data: {
    url: '',
    notices: '',
  },

  onLoad() {
    wx.cloud.database().collection('index').doc('b00064a76054bf6b0adc04827ae254ba').get().then(
      res => {
        // console.log(res.data.images)
        this.setData({
          url: res.data.images,
          notices: res.data.notices,
        })
      }
    )
  },
  onShow() {
    wx.cloud.database().collection('index').doc('b00064a76054bf6b0adc04827ae254ba').get().then(
      res => {
        //  console.log(res.data)
        this.setData({
          url: res.data.images,
          notices: res.data.notices,
        })
      }
    )
  },
  qushi() {                     
    wx.navigateTo({
      url: '../articleList/articleList?type=0',
    })
    wx.setNavigationBarTitle({
      title: '浴室环境'
    })
  },
  questions() {                
    wx.navigateTo({
      url: '../articleList/articleList?type=1',
    })
    wx.setNavigationBarTitle({
      title: '疑问互答'
    })
  },
  sight() {                 
    wx.navigateTo({
      url: '../articleList/articleList?type=2',
    })
    wx.setNavigationBarTitle({
      title: '浴室风光'
    })
  },
  love() {                 
    wx.navigateTo({
      url: '../articleList/articleList?type=3',
    })
    wx.setNavigationBarTitle({
      title: '相约洗浴'
    })
  },
  activityPage() {         
    wx.navigateTo({
      url: '../weather/weather',
    })
    wx.setNavigationBarTitle({
      title: '今日天气'
    })
  },
  chengji() {          
    wx.navigateTo({
      url: './cet/cet',
    })
    wx.setNavigationBarTitle({
      title: '每日评分'
    })
  },
})