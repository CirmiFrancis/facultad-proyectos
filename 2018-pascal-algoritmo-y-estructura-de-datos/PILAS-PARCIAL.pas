program PILAS;
uses crt;

type
        tregi = record
                cima:integer;
                dato:array[1..20] of char;
        end;

var
        votro:char;
        vdato:char;
        vexito:boolean;
        vpilas:tregi;

procedure INICIALIZAR (VAR ppilas:tregi);
begin
        ppilas.cima:=0;
end;

function PILALLENA (ppilas:tregi):boolean;
begin
        PILALLENA:=ppilas.cima=20;
end;

function PILAVACIA (ppilas:tregi):boolean;
begin
        PILAVACIA:=ppilas.cima=0;
end;

procedure METER (VAR ppilas:tregi; pdato:char);
begin
        if PILALLENA(ppilas)=true then
                writeln('PILA LLENA')
        else
                begin
                        ppilas.cima:=ppilas.cima+1;
                        ppilas.dato[ppilas.cima]:=pdato;
                end;
end;

procedure SACAR (VAR ppilas:tregi; VAR pdato:char; VAR pexito:boolean);
begin
        if PILAVACIA(ppilas)=true then
                begin
                        pexito:=false;
                        writeln('PILA VACIA');
                end
        else
                begin
                        pexito:=true;
                        pdato:=ppilas.dato[ppilas.cima];
                        ppilas.cima:=ppilas.cima-1;
                end;
end;

BEGIN
        votro:='s';
        INICIALIZAR (vpilas);
        while votro <> 'n' do
                begin
                   readln(vdato);
                   METER(vpilas,vdato);
                   readln(votro);
                end;
        votro:='s';
        while votro <> 'n' do
                begin
                        SACAR(vpilas,vdato,vexito);
                        if vexito=true then
                                writeln(vdato);
                        readln(votro);
                end;
END.