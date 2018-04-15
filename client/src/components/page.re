type search = {
  offset: int,
  limit: int
};

type action =
  | Navigate(search);

type state = {search};

let search_to_tuple = (search: string) : search =>
  Js.String.split("&", search)
  |> Array.to_list
  |> List.fold_left(
       (acc, elem) =>
         elem
         |> Js.String.split("=")
         |> Array.to_list
         |> (
           split =>
             switch split {
             | ["offset", value] => {...acc, offset: int_of_string(value)}
             | ["limit", value] => {...acc, limit: int_of_string(value)}
             | _ => acc
             }
         ),
       {limit: 0, offset: 0}
     );

let component = ReasonReact.reducerComponent("Page");

let make = (~title: string, _children) => {
  ...component,
  initialState: () => {offset: 0, limit: 100},
  reducer: (action, _state) =>
    switch action {
    | Navigate(search) => ReasonReact.Update(search)
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url => {
          let result = url.search |> search_to_tuple;
          switch url.search {
          | _ => self.send(Navigate(result))
          };
        }),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self =>
    <div>
      <div> <h1> <Text value=title /> </h1> </div>
      <Table limit=self.state.limit offset=self.state.offset />
      <br />
      <Pagination limit=self.state.limit offset=self.state.offset />
    </div>
};