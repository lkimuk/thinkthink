import QtQuick
import QtQuick.Controls

Item {
    //property int videoAreaHeight
    //anchors.fill: parent // without anchoring Item to parent, anchors.leftMargin will have no effect.
    //anchors.margins: 5
    height: gridArea.height

    ListModel {
        id: videoListModel

        ListElement { name: "UP: text1"; title: "故事的结局总是充满了遗憾"}
        ListElement { name: "UP: text2"; title: "电车难题与经济价值"}
        ListElement { name: "UP: text3"; title: "Title3" }
        ListElement { name: "UP: text4"; title: "打小就有出息" }
        ListElement { name: "UP: text5"; title: "Title5" }
        ListElement { name: "UP: text5"; title: "Title5" }
    }


    Rectangle {
        id: gridArea
        width: parent.width
        height: grid.cellHeight * Math.ceil(videoListModel.count / 5)
        color: "red"

        Component {
            id: contactDelegate

            Item {
                width: grid.cellWidth - 5
                height: grid.cellHeight - 5

                Column {
                    anchors.fill: parent
                    Image {
                        width: parent.width
                        height: parent.height - 60
                        source: "images/1209425.png"
                    }

                    Text {
                        text: title
                        width: parent.width
                        height: 40
                        font.pointSize: 11
                        wrapMode: Text.WordWrap
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 10

                        /*anchors.horizontalCenter: parent.horizontalCenter*/
                    }

                    Text {
                        id: authorName
                        height: 20
                        text: name
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
            cellHeight: cellWidth

            model: videoListModel
            delegate: contactDelegate
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
        }
    }

}
