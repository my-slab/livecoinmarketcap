let component = ReasonReact.statelessComponent("Page");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~message, _children) => {
  ...component,
  render: self =>
    <div>
      <h1 onClick=(self.handle(handleClick))>
        (ReasonReact.stringToElement(message))
      </h1>
      <Table />
    </div>
};