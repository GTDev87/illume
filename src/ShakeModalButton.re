open BsReactNative;


let squiggleImage : Packager.required = Packager.require("../../../assets/icons/squiggle.png");
let squiggleIcon : Image.imageSource = Image.Required(squiggleImage);

let defaultNote = {
  Control.id: -1,
  Control.text: "You have not added an awesome moment yet.",
  Control.color: Control.Red,
  Control.time: 0,
};

let selectRandomNote = (notes) => Utils.selectRandomFromList(notes, defaultNote);

type state = {selectedNote: Control.note};
type action =
  | SelectNote;

let component = ReasonReact.reducerComponent("ShakeModalButton");

let make = (~controlAction, ~scene, ~notes, _children) => {
  ...component, 
  initialState: () => ({selectedNote: defaultNote }),
  reducer: fun (action, state) =>
    switch action {
    | SelectNote => ReasonReact.Update({selectedNote: selectRandomNote(notes)})
    },
  render: (self) =>
    <View>
      <Modal2
        isVisible=(Js.Boolean.to_js_boolean(scene == Control.Shake))
        onBackdropPress={(_) => controlAction(Control.(ChangeScene(Home))); }
        backdropColor=Colors.yellowPrimaryString
        backdropOpacity=0.4
        animationOut="zoomOutDown"
        animationOutTiming=1000.
        backdropTransitionInTiming=1000.
        backdropTransitionOutTiming=1000.
      >
        <Text
          style=Style.(style([color("black")]))
          value=self.state.selectedNote.text
        />
      </Modal2>
      <SceneChangeButton
        onPress=((_event) => controlAction(Control.(ChangeScene(Shake))))
        icon=squiggleIcon
      />
    </View>
};
