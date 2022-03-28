import QtQuick
import QtQuick.Controls

Item {


    // 展示区域
    // 有背景的版本 其中implicitHeight供ScrollView推测出contentHeight
    ScrollView {
        id: videoLayoutScroll
        width: parent.width
        height: parent.height

        // 设置滚动条样式
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical: ScrollBar {
            parent: videoLayoutScroll.parent
            anchors.top: videoLayoutScroll.top
            anchors.left: videoLayoutScroll.right
            anchors.bottom: videoLayoutScroll.bottom
            height: videoLayoutScroll.availableHeight
        }

        clip: true

        Rectangle {
            width: parent.width
            implicitHeight:videoLayoutColumn.height
            color: "#50616d" // "#41555d"

            Column {
                id: videoLayoutColumn
                width: videoLayoutScroll.width
                spacing: 10

                Image {
                    id: hotVideoImage
                    width: parent.width
                    height: Math.ceil(parent.width / 4)
                    source: "../images/220302.png"
                }

                ////////////////////////////////////

                VideoItem {}

                ///////////////////////////////////
            }
        }
    }

//    ScrollView {
//        id: videoLayoutScroll
//        width: parent.width
//        height: parent.height

//        // 设置滚动条样式
//        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//        ScrollBar.vertical: ScrollBar {
//            parent: videoLayoutScroll.parent
//            anchors.top: videoLayoutScroll.top
//            anchors.left: videoLayoutScroll.right
//            anchors.bottom: videoLayoutScroll.bottom
//            height: videoLayoutScroll.availableHeight
//        }

//        clip: true

//        // 展示区域
//        // 无背景的版本
//        Column {
//            width: videoLayoutScroll.width
//            spacing: 10

////            Rectangle {
////                width: parent.width
////                height: 100
////                color: "red"
////            }

//            Image {
//                id: hotVideoImage
//                width: parent.width
//                height: Math.ceil(parent.width / 4)
//                source: "images/220302.png"
//            }

////            Rectangle {
////                width: parent.width
////                height: 100
////                color: "green"
////            }
//            ////////////////////////////////////

//            VideoItem {
//                // width: parent.width
//            }

//            ///////////////////////////////////
//        }
//    }
}
