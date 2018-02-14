type coin = {
  available_supply: string,
  hour_volume_24h: string,
  market_cap_usd: string,
  name: string,
  percent_change_24h: string,
  price: string,
  rank: string
};

type state =
  | Fail
  | Fetching
  | Success(list(coin));

type action =
  | CoinsFetch
  | CoinsFetchFail
  | CoinsFetchSuccess(list(coin));

let component = ReasonReact.reducerComponent("Currencies");

module Decode = {
  let decode = json =>
    Json.Decode.{
      available_supply: json |> field("available_supply", string),
      hour_volume_24h: json |> field("24h_volume_usd", string),
      market_cap_usd: json |> field("market_cap_usd", string),
      name: json |> field("name", string),
      percent_change_24h: json |> field("percent_change_24h", string),
      price: json |> field("price_usd", string),
      rank: json |> field("rank", string)
    };
  let coins = json => json |> Json.Decode.list(decode);
};

let make = (~columns, _children) => {
  ...component,
  initialState: _state => Fetching,
  reducer: (action, _state) =>
    switch action {
    | CoinsFetch =>
      ReasonReact.UpdateWithSideEffects(
        Fetching,
        (
          self =>
            Js.Promise.(
              Fetch.fetch("https://api.coinmarketcap.com/v1/ticker/")
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> Decode.coins
                   |> (coins => self.send(CoinsFetchSuccess(coins)))
                   |> resolve
                 )
              |> catch(_err => Js.Promise.resolve(self.send(CoinsFetchFail)))
              |> ignore
            )
        )
      )
    | CoinsFetchFail => ReasonReact.Update(Fail)
    | CoinsFetchSuccess(coins) => ReasonReact.Update(Success(coins))
    },
  didMount: self => {
    self.send(CoinsFetch);
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
          |> List.map(coin =>
               <tr key=coin.name>
                 <td> (ReasonReact.stringToElement(coin.rank)) </td>
                 <td> (ReasonReact.stringToElement(coin.name)) </td>
                 <td> (ReasonReact.stringToElement(coin.market_cap_usd)) </td>
                 <td> (ReasonReact.stringToElement(coin.price)) </td>
                 <td> (ReasonReact.stringToElement(coin.hour_volume_24h)) </td>
                 <td>
                   (ReasonReact.stringToElement(coin.available_supply))
                 </td>
                 <td>
                   (ReasonReact.stringToElement(coin.percent_change_24h))
                 </td>
               </tr>
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        }
      )
    </tbody>
};