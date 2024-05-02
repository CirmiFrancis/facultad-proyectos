program ejercicio3_modelo_de_parcial;
var
        vns,vnsm1,vnsm2,c:integer;
        vap,vapm1,vapm2:string[20];
begin
        vnsm1:=-10000;
        vnsm2:=-10000;
        for c:=1 to 4 do
                begin
                        readln(vns);
                        readln(vap);
                        if vns>vnsm1 then
                                begin
                                        vnsm2:=vnsm1;
                                        vapm2:=vapm1;
                                        vnsm1:=vns;
                                        vapm1:=vap;
                                end
                        else
                        if vns>vnsm2 then
                                begin
                                        vnsm2:=vns;
                                        vapm2:=vap;
                                end;
                end;                 writeln(vnsm1);
                writeln(vnsm2);
end.
