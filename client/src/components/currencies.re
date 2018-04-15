type state =
  | Fail
  | Fetching
  | Success(list(Coin.coin));

type action =
  | FetchCoins
  | FetchCoinsFail
  | FetchCoinsSuccess(list(Coin.coin));

let component = ReasonReact.reducerComponent("Currencies");

let make = (~columns, ~sort_by, ~direction, ~offset, _children) => {
  ...component,
  initialState: _state => Fetching,
  reducer: (a, _state) =>
    switch a {
    | FetchCoins =>
      ReasonReact.UpdateWithSideEffects(
        Fetching,
        (
          self =>
            Coin.fetch_coins(
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