
open Jest;

test("addition", (_) =>
  Expect.(expect(10 + 10) |> toBe(20))
);