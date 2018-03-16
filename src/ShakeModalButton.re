open BsReactNative;


let squiggleImage : Packager.required = Packager.require("../../../assets/icons/squiggle.png");
let squiggleIcon : Image.imageSource = Image.Required(squiggleImage);

let defaultNote : Control.note = Control.{
  id: -1,
  text: "You have not added an awesome moment yet.",
  color: Control.Red,
  time: 0,
};

let iconFontSize = 80;
let marginLeftCardContent = 5.;

type icon =
  | Heart
  | Smile
  | Happy;

let headerFooterTextStyle = Style.(style([
  marginLeft(Pct(marginLeftCardContent)),
  marginVertical(Pct(5.)),
  color("gray"),
  alignItems(Center),
  fontFamily("Arial Rounded MT Bold"),
]));

let iconStyle = Style.(style([
  alignItems(Center),
]));

let iconViewStyle = Style.(style([
  marginLeft(Pct(marginLeftCardContent)),
]));

let textStyle = Style.(style([
  marginLeft(Pct(marginLeftCardContent)),
  fontFamily("Arial Rounded MT Bold"),
  fontSize(Float(40.)),
]));

let choiceToIcon = (iconType) =>
  switch (iconType) {
  | Heart => <EnTypo name="heart" size=iconFontSize color="black" /*style=iconStyle*/ />
  | Smile => <SimpleLineIcons name="emotsmile" size=iconFontSize color="black" /*style=iconStyle*/ />
  | Happy => <FontAwesome name="child" size=iconFontSize color="black" /*style=iconStyle*/ />
  };

let iconChoices = [Heart, Smile, Happy];

let chooseRandomIcon = () => Utils.selectRandomFromList(iconChoices, Heart);

let selectRandomNote = (notes) => Utils.selectRandomFromList(notes, defaultNote);

type state = {selectedNote: Control.note, icon};
type action =
  | SelectNote;

let component = ReasonReact.reducerComponent("ShakeModalButton");

let make = (~controlAction, ~scene, ~notes, _children) => {
  ...component, 
  initialState: () => ({selectedNote: defaultNote, icon: Heart }),
  reducer: fun (action, _state) =>
    switch action {
    | SelectNote =>
      ReasonReact.UpdateWithSideEffects(
        {selectedNote: selectRandomNote(notes), icon: chooseRandomIcon()},
        (_self => controlAction(Control.(ChangeScene(Shake))))
      ) /* investigate this */
    },
  render: (self) =>
    <View
      style=Style.(style([
        flex(1.)
      ]))
    >
      <Modal2
        isVisible=(Js.Boolean.to_js_boolean(scene == Control.Shake))
        onBackdropPress={(_) => controlAction(Control.(ChangeScene(Home))); }
        animationOut="zoomOutDown"
        animationOutTiming=1000.
        backdropTransitionInTiming=1000.
        backdropTransitionOutTiming=1000.
        style=Style.(style([
          margin(Pt(0.)),
          marginTop(Pt(Dimension.topBarHeight)),
        ]))
      >
        <TouchableOpacity
          style=Style.(style([
            flex(1.),
          ]))
          onPress=(() => controlAction(Control.(ChangeScene(Home))))
        >
          <Card2
            style=Style.(style([
              backgroundColor(self.state.selectedNote.color |> Colors.colorToActualColor),
              flex(1.),
            ]))
          >
            <Grid>
              <Row size=1 >
                <Text
                  value="SHUFFLECARD"
                  style=headerFooterTextStyle
                />
              </Row>
              <Row size=4 />
              <Row size=2>
                <View style=iconViewStyle>
                  { choiceToIcon(self.state.icon) }
                </View>
              </Row>
              <Row size=4>
                <Text style=textStyle value=self.state.selectedNote.text />
              </Row>
              <Row size=1>
                <Text style=headerFooterTextStyle value="Keep those good vibes rolling" />
              </Row>
            </Grid>
            
          </Card2>
        </TouchableOpacity>
      </Modal2>
      <SceneChangeButton
        onPress=((_event) => self.send(SelectNote))
        icon=squiggleIcon
      />
    </View>
};
