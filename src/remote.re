
type t 'err 'ok =
  | NotAsked
  | Pending
  | Error 'err
  | Ready 'ok
  ;
let encoder errEncoder valueEncoder value => {
  switch (value) {
  | NotAsked => Js.Json.string "NotAsked"
  | Pending => Js.Json.string "Pending"
  | Error err => errEncoder err
  | Ready v => valueEncoder v
  };
};

let map f remote => 
  switch remote {
  | NotAsked => NotAsked
  | Pending => Pending
  | Error e => Error e
  | Ready x => Ready (f x)
  };

let chain f remote => 
  switch remote {
  | NotAsked => NotAsked
  | Pending => Pending
  | Error e => Error e
  | Ready x => f x
  };

let isNotAsked remote => switch (remote) {
| NotAsked => true
| _ => false
};

let isPending remote => switch (remote) {
| Pending => true
| _ => false
};

let isError remote => switch (remote) {
| Error _ => true
| _ => false
};

let isReady remote => switch (remote) {
| Ready _ => true
| _ => false
};
