type state =
  | Fail
  | Fetching
  | Success(list(Coin.coin));

type action =
  | FetchCoins
  | FetchCoinsFail
  | FetchCoinsSuccess(list(Coin.coin));

let component = ReasonReact.reducerComponent("Currencies");

let make = (~columns, ~direction, ~limit, ~offset, ~sort_by, _children) => {
  ...component,
  initialState: _state => Fetching,
  reducer: (action, _state) =>
    switch action {
    | FetchCoins =>
      ReasonReact.UpdateWithSideEffects(
        Fetching,
        (
          self =>
            Coin.fetch_coins(
              limit,
              offset,
              coins => self.send(FetchCoinsSuccess(coins)),
              self.send(FetchCoinsFail)
            )
        )
      )
    | FetchCoinsFail => ReasonReact.Update(Fail)
    | FetchCoinsSuccess(coins) => ReasonReact.Update(Success(coins))
    },
  didMount: self => {
    self.send(FetchCoins);
    ReasonReact.NoUpdate;
  },
  willReceiveProps: self => {
    self.send(FetchCoins);
    self.state;
  },
  render: self =>
    <tbody>
      (
        switch self.state {
        | Fail => <Message columns text="Fail" />
        | Fetching => <Message columns text="Fetching" />
        | Success(coins) =>
          coins
          |> Coin.sort_coins(sort_by, direction)
          |> List.map(coin => <Currency coin />)
          |> Array.of_list
          |> ReasonReact.arrayToElement
        }
      )
    </tbody>
};