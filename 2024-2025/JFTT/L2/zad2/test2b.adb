with Ada.Text_IO; use Ada.Text_IO;

procedure Test2 is
begin
    Put_Line ("=== Ada ===");
    Put_Line ("--- Not a comment ---");

    Put_Line ("""-- Not comment either");

    Put_Line (
        "Result:" & Integer'Image(2
    ));
end Test2;
