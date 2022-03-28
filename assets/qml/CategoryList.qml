import QtQuick
import QtQuick.Controls


FocusScope {
    id: root

    //CategoryFeeds { id: categoryFeeds }
    property string popup_text

    Popup {
        id: popup
        x: 100
        y: 100
        width: 200
        height: 200
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        contentItem: Text {
            text: popup_text
        }
    }

    ListView {
        id: categories
        width: parent.width
        height: parent.height
        keyNavigationWraps: true
        clip: true
        focus: true

        model: videoCategoryController.model()

        delegate: ItemDelegate {
            id: control
            implicitWidth: categories.width
            implicitHeight:40
            text: name

            contentItem: Text {
                text: parent.text
                font: parent.font
                color: parent.enabled ? (control.down ? "#f2fdff" : "#f2fdff") : "#f2fdff"
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.Wrap
            }

            background: Rectangle {
                id: listViewBackground
                implicitWidth: parent.width
                implicitHeight: parent.height
                opacity: 0.6
                color: control.highlighted ? (control.hovered ? "#50616d" : "#3d3b4f")
                                           : (control.hovered ? "#50616d" : "#758a99")
            }

            highlighted: ListView.isCurrentItem

            onClicked: {
                categories.forceActiveFocus()
                categories.currentIndex = model.index
                popup_text = model.name
                popup.open()
            }
        }

    }

    ScrollArea {
        id: listScrollBar

        orientation: Qt.Vertical
        height: categories.height;
        width: 8
        scrollArea: categories;
        anchors.right: categories.right
    }

}
