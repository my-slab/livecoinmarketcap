type action =
  | Click(string, Direction.direction);

type state = {
  direction: Direction.direction,
  key: string
};

type column = {
  display: string,
  key: string
};

let component = ReasonReact.reducerComponent("Table");

let columns = [
  {display: "#", key: "rank"},
  {display: "Name", key: "name"},
  {display: "Market Cap", key: "market_cap_usd"},
  {display: "Price", key: "price"},
  {display: "Volume (24h)", key: "24h_volume_usd"},
  {display: "Circulating Supply", key: "available_supply"},
  {display: "Change (24h)", key: "percent_change_24h"}
];

let toggleDirection = direction =>
  switch direction {
  | Direction.Asc => Direction.Desc
  | Direction.Desc => Direction.Asc
  };

let make = _children => {
  ...component,
  initialState: () => {
    key: columns |> List.hd |> (column => column.key),
    direction: Desc
  },
  reducer: (action, _state) =>
    switch action {
    | Click(key, direction) =>
      ReasonReact.Update({direction: toggleDirection(direction), key})
    },
  render: self =>
    <table>
      <thead>
        <tr>
          (
            columns
            |> List.map(column =>
                 <th
                   key=column.key
                   onClick=(
                     _event =>
                       self.send(Click(column.key, self.state.direction))
                   )>
                   (
                     self.state.key == column.key ?
                       <Chevron direction=self.state.direction /> :
                       ReasonReact.nullElement
                   )
                   (ReasonReact.stringToElement(column.display))
                 </th>
               )
            |> Array.of_list
            |> ReasonReact.arrayToElement
          )
        </tr>
      </thead>
      <Currencies columns=(List.length(columns)) />
    </table>
};