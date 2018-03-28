let component = ReasonReact.statelessComponent("Text");

let toLocale: float => string = [%bs.raw
  {|
    function(value) {
      const number = Number(value);
      const { language = 'us-US' } = navigator;

      return number.toLocaleString(language);
    }
  |}
];

let make = (~value: float, _children) => {
  ...component,
  render: _self => <span> <Text value=(toLocale(value)) /> </span>
};