type route =
  | Detail(string)
  | List;

type action =
  | Navigate(route);

type state = {route};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {route: List},
  reducer: (action, _state) =>
    switch action {
    | Navigate(Detail(code)) => ReasonReact.Update({route: Detail(code)})
    | Navigate(List) => ReasonReact.Update({route: List})
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch url.path {
          | [] => self.send(Navigate(List))
          | [symbol] => self.send(Navigate(Detail(symbol)))
          | _ => self.send(Navigate(List))
          }
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self =>
    <div>
      (
        switch self.state.route {
        | Detail(symbol) => <Text value=symbol />
        | List => <Page title="Cryptocurrency Market Capitalizations" />
        }
      )
    </div>
};