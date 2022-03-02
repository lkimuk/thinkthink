import QtQuick
import QtQuick.Controls

Item {
    //property int videoAreaHeight
    //anchors.fill: parent // without anchoring Item to parent, anchors.leftMargin will have no effect.
    //anchors.margins: 5
    height: gridArea.height

    ListModel {
        id: videoListModel

        ListElement { author: "UP: 大笨蛋"; title: "故事的结局总是充"; date: "2-27" }
        ListElement { author: "UP: 小兔子"; title: "电车难题与经济价值"; date: "2-28" }
        ListElement { author: "UP: 哈哈哈哈哈"; title: "Title3";  date: "3-1" }
        ListElement { author: "UP: 奇奇怪怪"; title: "打小就有出息"; date: "3-2" }
    }


    Rectangle {
        id: gridArea
        width: parent.width
        height: grid.cellHeight * Math.ceil(videoListModel.count / 5)
        color: "red"

        Component {
            id: videoItemDelegate

            Item {
                width: grid.cellWidth - 5
                height: grid.cellHeight - 5

                Column {
                    anchors.fill: parent
                    spacing: 3
                    Image {
                        id: videoImage
                        width: parent.width
                        height: Math.ceil(parent.height / 5) * 3
                        asynchronous: true
                        cache: false
                        source: "images/1209425.png"
                    }

                    Text {
                        id: videoTitle
                        text: title
                        width: parent.width
                        height: Math.ceil((parent.height - videoImage.height) / 2)
                        font.pointSize: 11
                        wrapMode: Text.WordWrap
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 10

                        /*anchors.horizontalCenter: parent.horizontalCenter*/
                    }

                    Text {
                        id: authorName
                        text: author + " · " + date
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: grid.currentIndex = index
                }
            }
        }

        GridView {
            id: grid
            anchors.fill: parent
            cellWidth: parent.width / 5
            cellHeight: Math.ceil(cellWidth / 4) * 3

            model: videoListModel
            delegate: videoItemDelegate
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
        }
    }

}
