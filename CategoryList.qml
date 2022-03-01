import QtQuick
import QtQuick.Controls


FocusScope {
    id: root

    CategoryFeeds { id: categoryFeeds }

    ListView {
        id: categories
        width: parent.width
        height: parent.height
        keyNavigationWraps: true
        clip: true
        focus: true

        model: categoryFeeds

        delegate: ItemDelegate {
            id: control
            implicitWidth: categories.width
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
                categories.forceActiveFocus()
                categories.currentIndex = model.index
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
