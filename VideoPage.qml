import QtQuick
import QtQuick.Controls


ScrollView {

    contentHeight: 200 + videotest.height

    Rectangle {
        id: hotVideFrame
        anchors.fill: parent
        color: "pink"

        Rectangle {
            id: hotVideoArea
            width: parent.width
            height: 200
            color: "yellow"

            Rectangle {
                id: overlay
                width: 200
                height: parent.height
                anchors.right: parent.right

                color: "#003499"
                opacity: 0.2

                visible: true
            }
        }

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
