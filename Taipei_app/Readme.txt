App架構:
分為三個activity: MainActivity, dataActivity, MapActivity，
分別實行3個畫面(layout):activity_main, datalayout, maplayout。
Main這一層主要是選單，看使用者想要獲取哪方面的資訊，目前的想法
是將台北市的資訊整合在一起，但目前只有實作台北市施工資訊的部分。
data層是將網路讀來的資料擷取我自己認為較重要的放上來，並且按照
各個不同的區來做排序。Map層是將施工地點放到googleMap上並且標記
圖示。

實作方式:
Main層除了一些排版的處理外，還加了按下"今日施工資訊按鈕"後，要
用url下載資訊的處理，這邊我是用AsyncTask這個class來處理，用
onPreExecute秀出等待的訊息，doInBackground來處理讀url的部分，並將
資料存到nodeList中。onProgressUpdate讓使用者知道進行到哪裡。
onPostExecute將讀來的資料用一個TreeSet並按照"區"來排序並且輸出字串
到data層。

data層的功夫比較少，只有按下"地圖"按鈕後會切到Map層這個功能。

Map層主要是連結地圖的處理。用setCamera將整個畫面切到以台北101為中心。
前面處理的data獲得的地址用geocoder找到經緯度並且標記在地圖上，而我用的
icon是上網抓的google圖示。

特色:
1.按照地區來排序施工資訊，如此一來使用者可以就自己待的區域快速檢視
附近有無施工。
2.用googlemap標示施工所在地點。但是目前還未真正完成，未來希望達到的
目標是結合導航系統，讓導航可以避開在施工的地方。


檔案的部分:
drawable,layout, values是直接從(Application)/app/src/main/res拿出的檔案
AndroidManifest則是從(Application)/app/src/main/拿出的
sourceCode裡面的三個java檔則是主要的javaCode。