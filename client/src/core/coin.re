let api = "https://api.coinmarketcap.com/v1/ticker/";

type coin = {
  available_supply: float,
  hour_volume_24h: float,
  market_cap_usd: float,
  name: string,
  percent_change_24h: float,
  price: float,
  rank: int,
  symbol: string
};

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
      rank: json |> field("rank", string) |> int_of_string,
      symbol: json |> field("symbol", string)
    };
  let coins = json => json |> Json.Decode.list(decode);
};

let fetch_coins = (success, error) =>
  Js.Promise.(
    Fetch.fetch(api)
    /* ++ string_of_int(offset) */
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Decode.coins |> success |> resolve)
    |> catch(err => {
         Js.log(err);
         Js.Promise.resolve(error);
       })
    |> ignore
  );

let sort_coins = (key, direction, coins: list(coin)) =>
  (
    switch key {
    | "rank" =>
      coins |> List.sort((a: coin, b: coin) => compare(a.rank, b.rank))
    | "name" =>
      coins |> List.sort((a: coin, b: coin) => compare(a.name, b.name))
    | "market_cap_usd" =>
      coins
      |> List.sort((a: coin, b: coin) =>
           compare(a.market_cap_usd, b.market_cap_usd)
         )
    | "price" =>
      coins |> List.sort((a: coin, b: coin) => compare(a.price, b.price))
    | "hour_volume_24h" =>
      coins
      |> List.sort((a: coin, b: coin) =>
           compare(a.hour_volume_24h, b.hour_volume_24h)
         )
    | "available_supply" =>
      coins
      |> List.sort((a: coin, b: coin) =>
           compare(a.available_supply, b.available_supply)
         )
    | "percent_change_24h" =>
      coins
      |> List.sort((a: coin, b: coin) =>
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