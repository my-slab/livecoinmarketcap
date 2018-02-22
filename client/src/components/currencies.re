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
};

let fetch_coins = (self: ReasonReact.self('a, 'b, 'c), offset) =>
  Js.Promise.(
    Fetch.fetch(
      "https://api.coinmarketcap.com/v1/ticker/?start="
      ++ string_of_int(offset)
    )
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
  );

let sort_coins = (key, direction, coins) =>
  (
    switch key {
    | "rank" => coins |> List.sort((a, b) => compare(a.rank, b.rank))
    | "name" => coins |> List.sort((a, b) => compare(a.name, b.name))
    | "market_cap_usd" =>
      coins |> List.sort((a, b) => compare(a.market_cap_usd, b.market_cap_usd))
    | "price" => coins |> List.sort((a, b) => compare(a.price, b.price))
    | "hour_volume_24h" =>
      coins
      |> List.sort((a, b) => compare(a.hour_volume_24h, b.hour_volume_24h))
    | "available_supply" =>
      coins
      |> List.sort((a, b) => compare(a.available_supply, b.available_supply))
    | "percent_change_24h" =>
      coins
      |> List.sort((a, b) =>
           compare(a.percent_change_24h, b.percent_change_24h)
         )
    | _ => coins
    }
  )
  |> (
    switch direction {
    | Sort.Asc => List.rev
    | Sort.Desc => (i => i)
    }
  );

let make = (~columns, ~sort_by, ~direction, _children) => {
  ...component,
  initialState: _state => Fetching,
  reducer: (action, _state) =>
    switch action {
    | CoinsFetch =>
      ReasonReact.UpdateWithSideEffects(
        Fetching,
        (self => fetch_coins(self, 0))
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
          |> sort_coins(sort_by, direction)
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