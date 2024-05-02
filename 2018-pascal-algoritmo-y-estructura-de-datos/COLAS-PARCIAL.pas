program COLAS;
uses crt;

type
        tregi = record
                frente:integer;
                ultimo:integer;
                dato:array[1..20] of char;
        end;

var
        votro:char;
        vdato:char;
        vexito:boolean;
        vcola:tregi;

procedure INICIALIZAR(VAR pcola:tregi);
begin
        pcola.frente:=1;
        pcola.ultimo:=1;
end;

function COLALLENA(pcola:tregi):boolean;
var
        vsig:integer;
begin
        vsig:=(pcola.ultimo MOD 20)+1;
        COLALLENA:=pcola.frente=vsig;
end;

function COLAVACIA(pcola:tregi):boolean;
begin
        COLAVACIA:=pcola.frente=pcola.ultimo;
end;

procedure METER(VAR pcola:tregi; pdato:char);
begin
        if COLALLENA(pcola)=true then
                writeln('COLA LLENA')
        else
                begin
                        pcola.dato[pcola.ultimo]:=pdato;
                        pcola.ultimo:=(pcola.ultimo MOD 20)+1;
                end;
end;

procedure SACAR(VAR pcola:tregi; VAR pdato:char; VAR pexito:boolean);
begin
        if COLAVACIA(pcola)=true then
                begin
                        pexito:=false;
                        writeln('COLA VACIA');
                end
        else
                begin
                        pexito:=true;
                        pdato:=pcola.dato[pcola.frente];
                        pcola.frente:=(pcola.frente MOD 20)+1;
                end;
end;


BEGIN
        votro:='s';
        INICIALIZAR(vcola);
        while votro <> 'n' do
                begin
                        readln(vdato);
                        METER(vcola,vdato);
                        readln(votro);
                end;
        votro:='s';
        while votro <> 'n' do
                begin
                        SACAR(vcola,vdato,vexito);
                        if vexito = true then
                                writeln(vdato);
                        readln(votro);
                end;
END.