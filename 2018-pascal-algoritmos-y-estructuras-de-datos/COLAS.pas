program cola;
uses crt;

type
        tregi=record
         frente:integer;
         ultimo:integer;
         dato:array [1..5] of char;
end;

var
        vdato:char;
        votro:char;
        vexito:boolean;
        vcola:tregi;

procedure INICIALIZAR (VAR pcola:tregi);
        begin
         pcola.frente:=1;
         pcola.ultimo:=1;
        end;

function COLALLENA (pcola:tregi):boolean;
         var
          vsig:integer;
         begin
          vsig:= (pcola.ultimo MOD 5) + 1;
          colallena:= pcola.frente = vsig;
         end;

function COLAVACIA (pcola:tregi):boolean;
         begin
          colavacia:= pcola.frente = pcola.ultimo;
         end;

procedure METER (VAR pcola:tregi; pdato:char);
        begin
         if colallena(pcola) = true then
          writeln('Cola Llena')
         else
          begin
           pcola.dato[pcola.ultimo]:=pdato;
           pcola.ultimo:=(pcola.ultimo MOD 5) + 1;
          end;
        end;

procedure SACAR (VAR pcola:tregi; VAR pdato:char; VAR pexito:boolean);
        begin
         if colavacia(pcola) = true then
          begin
           pexito:=false;
           writeln('Cola Vacia');
          end
         else
          begin
           pexito:=true;
           pdato:=pcola.dato[pcola.frente];
           pcola.frente:=(pcola.frente MOD 5) + 1;
          end;
        end;

BEGIN
        INICIALIZAR(vcola);
        votro:='s';
        while votro <> 'n' do
         begin
          readln(vdato);
          METER(vcola,vdato);
          readln(votro);
         end;
        votro:= 's';
        while votro <> 'n' do
         begin
          SACAR(vcola,vdato,vexito);
          if vexito = true then
           writeln(vdato);
          readln(votro);
         end;
END.
