type route =
  | Detail(string)
  | List;

type action =
  | Navigate(route);

type state = {page: route};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {page: List},
  reducer: (action, _state) =>
    switch action {
    | Navigate(Detail(code)) => ReasonReact.Update({page: Detail(code)})
    | Navigate(List) => ReasonReact.Update({page: List})
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
        switch self.state.page {
        | Detail(symbol) => <Text value=symbol />
        | List => <Page title="Cryptocurrency Market Capitalizations" />
        }
      )
    </div>
};