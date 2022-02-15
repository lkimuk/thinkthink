import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts

FocusScope {
    id: root

    ListModel {
        id: listViewModel

        ListElement {
            name: "First"
        }
        ListElement {
            name: "Second"
        }
        ListElement {
            name: "Third"
        }
    }

    ListView {
        id: listView
        width: 200
        height: 400
        keyNavigationWraps: true
        clip: true
        focus: true
        ScrollBar.vertical: ScrollBar { }

        model: listViewModel

        delegate: ItemDelegate {
            id: control
            implicitWidth: parent.width
            implicitHeight:40
            text: name

            contentItem: Text {
                text: parent.text
                font: parent.font
                color: parent.enabled ? (control.down ? "#17a81a" : "#21be2b") : "#bdbebf"
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.Wrap
            }

            background: Rectangle {
                id: listViewBackground
                implicitWidth: parent.width
                implicitHeight: parent.height
                opacity: enabled ? 1 : 0.3
                color: control.highlighted ? (control.hovered ? "#ff0000" : "#cc0000")
                                           : (control.hovered ? "#0000ff" : "#0000cc")
            }

            highlighted: ListView.isCurrentItem

            onClicked: {
                listView.forceActiveFocus()
                listView.currentIndex = model.index
            }
        }
    }
}
