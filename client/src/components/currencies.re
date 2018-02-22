type coin = {
  available_supply: float,
  hour_volume_24h: float,
  market_cap_usd: float,
  name: string,
  percent_change_24h: float,
  price: float,
  rank: int
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
      available_supply:
        json |> field("available_supply", string) |> float_of_string,
      hour_volume_24h:
        json |> field("24h_volume_usd", string) |> float_of_string,
      market_cap_usd:
        json |> field("market_cap_usd", string) |> float_of_string,
      name: json |> field("name", string),
      percent_change_24h:
        json |> field("percent_change_24h", string) |> float_of_string,
      price: json |> field("price_usd", string) |> float_of_string,
      rank: json |> field("rank", string) |> int_of_string
    };
  let coins = json => json |> Json.Decode.list(decode);
  Js.log(coins);
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
              |> catch(err => {
                   Js.log(err);
                   Js.Promise.resolve(self.send(CoinsFetchFail));
                 })
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
          /* |> List.sort((a, b)
             /* Must use Map for dynamic access as records are static */
             => a[self.state.key] > b[self.state.key] ? 1 : (-1)) */
          |> List.map(coin =>
               <tr key=coin.name>
                 <td> <Int value=coin.rank /> </td>
                 <td> <Text value=coin.name /> </td>
                 <td> <Float value=coin.market_cap_usd /> </td>
                 <td> <Float value=coin.price /> </td>
                 <td> <Float value=coin.hour_volume_24h /> </td>
                 <td> <Float value=coin.available_supply /> </td>
                 <td> <Percentage value=coin.percent_change_24h /> </td>
               </tr>
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        }
      )
    </tbody>
};