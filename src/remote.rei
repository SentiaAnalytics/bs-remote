
type t 'err 'ok =
  | NotAsked
  | Pending
  | Error 'err
  | Ready 'ok
  ;
let encoder :  ('err => Js.Json.t) => ('a => Js.Json.t) => t 'err 'a => Js.Json.t;

let map : ('a => 'b ) => t 'err 'a => t 'err 'b;
let chain : ('a => t 'err 'b ) => t 'err 'a => t 'err 'b;
  
let isNotAsked : t 'err 'value => bool;
let isPending : t 'err 'value => bool;
let isError : t 'err 'value => bool;
let isReady : t 'err 'value => bool;