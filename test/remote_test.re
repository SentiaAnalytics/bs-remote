open Tape;
open Remote;

test "isNotAsked should return true if NotAsked" (fun t => {
  t.plan 1;
  t.ok (Remote.isNotAsked (NotAsked))
});

test "isPending should return true if pending" (fun t => {
  t.plan 1;
  t.ok (Remote.isPending (Pending))
});

test "isError should return true if ready" (fun t => {
  t.plan 1;
  t.ok (Remote.isError (Error "Err"))
});

test "isReady should return true if ready" (fun t => {
  t.plan 1;
  t.ok (Remote.isReady (Ready "ready"))
});

test "map should map ready values" (fun t => {
  t.plan 1;
  let a = Ready 5;
  t.ok (switch (a |> Remote.map (fun n => n + 1)) {
  | Ready actual => actual == 6
  | _ => false
  })
});

test "map should do nothing for non ready values" (fun t => {
  t.plan 1;
  let a = Pending;
  let actual = Remote.map (fun n => n + 1) a;
  t.ok (Remote.isPending actual);
});

test "chain should chain ready values" (fun t => {
  t.plan 1;
  let a = Ready 5;
  let actual = Remote.chain (fun n => Error "some error") a;
  t.ok (switch actual {
  | Error err => err == "some error"
  | _ => false 
  });
});

test "chain should do nothing for non ready values" (fun t => {
  t.plan 1;
  let a = Pending;
  let actual = Remote.chain (fun n => Ready (n + 1)) a;
  t.ok (Remote.isPending actual);
});