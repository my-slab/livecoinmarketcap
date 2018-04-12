type action =
  | List
  | Detail(string);

type state = {page: action};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {page: List},
  reducer: (action, _state) =>
    switch action {
    | List => ReasonReact.Update({page: List})
    | Detail(symbol) => ReasonReact.Update({page: Detail(symbol)})
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch url.path {
          | [] => self.send(List)
          | [symbol] => self.send(Detail(symbol))
          | _ => self.send(List)
          }
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self =>
    <div>
      (
        switch self.state.page {
        | List => <Page title="Cryptocurrency Market Capitalizations" />
        | Detail(symbol) => <Text value=symbol />
        }
      )
    </div>
};