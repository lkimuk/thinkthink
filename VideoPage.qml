import QtQuick
import QtQuick.Controls


ScrollView {

    contentHeight: 200 + videotest.height

    Rectangle {
        id: hotVideFrame
        anchors.fill: parent
        color: "pink"

        Image {
            id: hotVideoArea
            width: parent.width
            height: Math.ceil(width / 4)
            source: "images/220302.png"

            Rectangle {
                id: overlay
                width: 200
                height: parent.height
                anchors.right: parent.right

                color: "#50616d"
                opacity: 0.7

                visible: true
            }
        }

//        Rectangle {
//            id: hotVideoArea
//            width: parent.width
//            height: 200
//            color: "yellow"

//            Rectangle {
//                id: overlay
//                width: 200
//                height: parent.height
//                anchors.right: parent.right

//                color: "#003499"
//                opacity: 0.2

//                visible: true
//            }
//        }

        Column {
            id: videotest

            anchors {
                left: hotVideoArea.left
                top: hotVideoArea.bottom
                right: hotVideoArea.right
                margins: 5
            }

            VideoItems {
                width: parent.width
            }
            VideoItems {
                width: parent.width
            }
        }
    }
}
