import bb.cascades 1.0


Container {
    background: Color.create("#000000")
    id: mainContainer
    objectName: "mainContainer"
    ImageView {
        imageSource: "asset:///active-frame.png"
        verticalAlignment: VerticalAlignment.Top
        horizontalAlignment: HorizontalAlignment.Center
        preferredHeight: 400
        preferredWidth: 400
        leftPadding: 50
        rightPadding: 50
        topPadding: 50
    }
    /*Label {
        id: label2
        objectName: "label2"
        text: qsTr("")
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Center
        textStyle.fontSizeValue: 20.0
        textStyle.color: Color.White
    }
    Label {
    	id: label1
    	objectName: "label2"
        text: qsTr("")
	    textStyle.fontSizeValue: 20.0
	    textStyle.color: Color.White
        horizontalAlignment: HorizontalAlignment.Center
    }*/
}
