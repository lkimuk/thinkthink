import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    width: parent.width
    height: videoItemColumn.height

//    VideoItemFeeds {
//        id: videoItemFeeds
//    }


    // 每个VideoItem列表
    Column {
        id: videoItemColumn
        width: parent.width
        spacing: 15


        // 分区标题区域
        RowLayout {
            id: videoItemHeader
            width: parent.width
            height: 20


            Text {
                text: qsTr("热门推荐")
                color: "#ffffff"
                font.pointSize: 14
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
               text: qsTr("换一换")

               contentItem: Text {
                   text: parent.text
                   font: parent.font
                   color: "#ffffff"
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
                   elide: Text.ElideRight
               }

               background: Rectangle {
                   color: "green"
                   border.color: "red"
                   border.width: 1
                   radius: 2
               }
           }

            Button {
                text: qsTr("更多")
                Layout.preferredWidth: 60
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 10
            }
        }

        //////////////////////////////
        GridView {
            id: videoGridView
            width: parent.width
            height: cellHeight * (Math.ceil(videoGridView.count / Math.floor(parent.width / cellWidth)))
            cellWidth: 270
            cellHeight: 165
            clip: true

            model: videoController.model()/*videoItemFeeds*/
            delegate: videoViewDelegate
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        }

        Component {
            id: videoViewDelegate

            Item {
                width: videoGridView.cellWidth
                height: videoGridView.cellHeight

                Column {
                    anchors.fill: parent

                    Image {
                        id: videoImage
                        width: parent.width - 5
                        height: parent.height - 60
                        asynchronous: true
                        //fillMode: Image.PreserveAspectFit
                        cache: true
                        //source: "../../images/1209425.png"
                        source: "https://www.tujuyun.com/upload/photo/imgSmall/20211204/b302bb40-6113-4fd7-9a78-0a4fb8771450_5208228_wantuju.jpg"
                    }

                    Text {
                        id: videoTitle
                        text: model.video_name
                        width: parent.width - 5
                        height: 40
                        font.pointSize: 11
                        wrapMode: Text.WordWrap
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 10
                        color: "#ffffff"

                        /*anchors.horizontalCenter: parent.horizontalCenter*/
                    }

                    Text {
                        id: authorName
                        text: model.uploader + " · " + model.upload_date
                        width: parent.width - 5
                        height: 15
                        color: "#e9f1f6"
                        font.pointSize: 8
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: videoGridView.currentIndex = index
                }
            }
        }

        ///////////////////////////////
    }

}
