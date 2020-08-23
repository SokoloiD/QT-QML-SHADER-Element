import QtQuick.Window 2.12
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick 2.6
import QtQuick.Controls 2.15
//import QtQuick.Controls 2.1
import QtQuick.Controls.Universal 2.0
import QMLImageFx 1
//import QtQuick 2.2

Window {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Image processing")

    SystemPalette { id: palette }
    color: Qt.darker(palette.window, 1.1)

    MenuBar {
                id: menuBar
                Menu {
                        title: "File"

                        Action {
                                id: actionOpenImage
                                text: "Открыть изображение"
                                onTriggered: {
                                              fileDialogLoad.open()
                                              }
                                    }

                        Action {
                                text: "Сохратить изображение"
                                id: menuActionSave
                                enabled: false
                                onTriggered: {
                                               fileDialogSave.open()
                                                }

                                 }
                        MenuSeparator { }
                        Action {
                                text: "Начать обработку"
                                id: menuActionStart
                                onTriggered: {
                                                imagefx.startFx( (radioButton501.checked)?0:1,
                                                                    spinBoxMatrix.value,
                                                                 spinBoxChunk.value)
                                         }
                                }
                        Action {
                                text: "Прервать обработку"
                                id: menuActionCancel
                                enabled: false
                                onTriggered: {  imagefx.cancelFx()

                                            }
                               }
                       MenuSeparator { }
                        Action {
                                text: "Выход"
                                onTriggered:{
                                            imagefx.cancelFx()
                                            Qt.quit()
                                            }
                                }
                         }
    }
    //! [filedialog]
    FileDialog {
                id: fileDialogLoad
                visible: false
                modality: Qt.WindowModal
                title: "Выберите файл картинки"

                selectExisting: true
                selectMultiple: false
                selectFolder: false
                nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
                selectedNameFilter: "All files (*)"
                sidebarVisible: true
                onAccepted: {
                            console.log("Accepted: " + fileUrls)
                            image1.source = fileUrls[0]
                            label1.text = fileUrls[0]
                            imagefx.loadImage(fileUrls[0])
                             }
                // onRejected: { console.log("Rejected") }
    }
    FileDialog {
                id: fileDialogSave
                visible: false
                modality: Qt.WindowModal
                title: "Сохранить файл как"

                selectExisting: false
                selectMultiple: false
                selectFolder: false
                nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
                selectedNameFilter: "All files (*)"
                sidebarVisible: true
                onAccepted: {
                            console.log("Accepted: " + fileUrls)
                             imagefx.saveImage(fileUrls[0])
                             }
    //            onRejected: { console.log("Rejected") }
            }
    //! [filedialog]



    Rectangle {
                id: bottomBar
                anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                         }
                height: buttonRow.height * 1.2
                color: Qt.darker(palette.window, 1.1)
                border.color: Qt.darker(palette.window, 1.3)
                Row {
                    id: buttonRow
                    spacing: 6
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    height: implicitHeight
                    width: parent.width
                    Button {
                            id: openButton
                            text: "Open"
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked:{ fileDialogLoad.open()
                            }
                    }
                    Button {
                            id: pictureButton
                            text: "Pictures"

                            anchors.verticalCenter: parent.verticalCenter
                            onClicked:{
                                        fileDialogLoad.folder = fileDialogLoad.shortcuts.pictures
                                         fileDialogLoad.open()
                                       }
                          }
                    Button {
                            id: homeButton
                            text: "Home"
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked: {
                                        fileDialogLoad.folder = fileDialogLoad.shortcuts.home
                                        fileDialogLoad.open()
                                        }
                             }
                    Button {
                            id: startButton
                            text: "Старт"
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked: {imagefx.startFx(  (radioButton501.checked)?0:1,
                                                        spinBoxMatrix.value,
                                                        spinBoxChunk.value)
                                        }
                            }
                    Button {
                            id: stopButton
                            text: "Стоп"
                            enabled: false
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked: {
                                        imagefx.cancelFx()
                                        }
                           }
                    Button {
                            id: saveButton
                            text: "Сохранить"
                            enabled: false
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked: {
                                        fileDialogSave.open()
                                        }
                            }
                }
    }
    ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: progressBar.top
                anchors.bottomMargin: 0
                RadioButton {
                            id: radioButton501
                            checked: true
                            text: qsTr("Фильтр 501 размытие")
                             }
                RadioButton {
                            id: radioButton511
                            text: qsTr("Фильтр 511 медианный")
                             }

                   }

    Label {
            y: 434
            text: "<b>Размер матрицы фильтра:</b> "
            anchors.left: spinBoxMatrix.left
            anchors.leftMargin: 0
            anchors.bottom: spinBoxMatrix.top
            anchors.bottomMargin: 0
           }

    ProgressBar {
                id: progressBar
                y: 381
                height: 29
                from: 0
                indeterminate: false
                to: 1
                anchors.bottomMargin: 22
                anchors.bottom: bottomBar.top
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                value: 0.8
               }

    SpinBox {
            id: spinBoxMatrix
            x: 428
            y: 341
            editable: true
            to: 64
            from: 3
            value: 8
            anchors.bottom: progressBar.top
            anchors.bottomMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 20
            }

    Label {
            id: label
            x: 12
            y: 153
            text: qsTr("<b>Файл изображения:</b> ")
            anchors.bottom: bottomBar.top
            anchors.bottomMargin: 13
            anchors.left: parent.left
            anchors.leftMargin: 29
          }


    Image {
            id: image1
            width: (parent.width/2-55 > parent.height-250)?parent.height-250 :parent.width/2 -55
            height: (parent.width/2-55 > parent.height-250)?parent.height-250 :parent.width/2 - 55
            anchors.left: parent.left
            anchors.leftMargin: 7
            anchors.top: parent.top
            anchors.topMargin: 50
            //   fillMode: Image.PreserveAspectFit
         }
    ImageFx {
            id:imagefx
            anchors.right: parent.right
            anchors.rightMargin: 7
            anchors.top: parent.top
            anchors.topMargin: 50
            width: (parent.width/2-55 > parent.height-250)?parent.height-250 :parent.width/2 -55
            height: (parent.width/2-55 > parent.height-250)?parent.height-250 :parent.width/2 - 55
            onJobStarted: {
                            startButton.enabled = false
                            openButton.enabled = false
                            pictureButton.enabled =false
                            homeButton.enabled =false
                            stopButton.enabled = true
                            spinBoxChunk.enabled = false
                            spinBoxMatrix.enabled  = false
                            radioButton501.enabled = false
                            radioButton511.enabled = false
                            menuActionStart.enabled = false
                            menuActionCancel.enabled = true

                         }

             onSetProgress:{
                            progressBar.value= newProgress
                           }
             onJobDone: {
                         messageDialogJobDone.visible = true
                         startButton.enabled = true
                         openButton.enabled = true
                         pictureButton.enabled =true
                         homeButton.enabled =true
                         stopButton.enabled = false
                         spinBoxChunk.enabled = true
                         spinBoxMatrix.enabled  = true
                         radioButton501.enabled = true
                         radioButton511.enabled = true
                         saveButton.enabled = true
                         menuActionSave.enabled = true
                         menuActionStart.enabled = true
                        }
             onErrorOccured: {
                             messageDialogError.text = errorDescript
                             messageDialogError.visible = true
                              }
          }


    Label {
            id: label1
            y: 416
            text: qsTr("Label")
            anchors.bottom: bottomBar.top
            anchors.bottomMargin: 13
            anchors.left: label.right
            anchors.leftMargin: 20
          }

    Label {
            x: 0
            y: 434
            text: "<b>шкала прогресса:</b> "
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: progressBar.top
            anchors.bottomMargin: 0
          }

     SpinBox {
             id: spinBoxChunk
             x: 250
             y: 311
             width: 144
             height: 40
             editable: true
             to: 64
             from: 8
             value: 8
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.bottom: progressBar.top
             anchors.bottomMargin: 30
            }

     Label {
             y: 434
             text: "<b>Размер ячейки map"
             anchors.bottom: spinBoxChunk.top
             anchors.bottomMargin: 0
             anchors.left: spinBoxChunk.left
             anchors.leftMargin: 0
             }
    MessageDialog {
                id: messageDialogJobDone
                title: "Работа закончена"
                property int icon: StandardIcon.Information
                text : "Работа закончена"
                visible: false
                modality: Qt.WindowModal

                 }
    MessageDialog {

                    id: messageDialogError
                    title: "Обнаружена ошибка"
                    property int icon: StandardIcon.Critical
                    text :  ""
                    visible: false
                    modality: Qt.WindowModal

                 }
}
/*##^##
Designer {
    D{i:16;anchors_x:0;anchors_y:90}D{i:17;anchors_x:0}D{i:18;anchors_height:100;anchors_x:7;anchors_y:34}
D{i:19;anchors_y:90}D{i:20;anchors_x:222}D{i:14;anchors_x:0}D{i:13;anchors_x:0}D{i:23;anchors_x:226}
D{i:21;anchors_height:100;anchors_x:7;anchors_y:34}D{i:24;anchors_x:0}D{i:26;anchors_x:0}
D{i:27;anchors_x:0}D{i:29;anchors_x:0}
}
##^##*/
