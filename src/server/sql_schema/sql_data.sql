start transaction;
DO
$$
DECLARE rootid int;
DECLARE measurand int;
DECLARE base int;
DECLARE metric_sys int;

BEGIN

select uid from users where name = 'ROOT' limit 1 into rootid;

insert into metric_system(name)
values ('SI')
returning id into metric_sys;

insert into measurands (name, description, dimension_symbol )
values('Electric current', '', 'I')
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, description, metric_system ) values
( rootid, 'ampere', 'A', measurand, 'The ampere is that constant current which, if maintained in two straight parallel conductors of infinite length, of negligible circular cross-section, and placed 1 meter apart in vacuum, would produce between these conductors a force equal to 2 x 10-7 newton per meter of length.', metric_sys)
returning uid into base;

insert into units (owner, name, symbol, measurand_id, base_unit, metric_system ) values
( rootid, 'tera ampere',  'TA', measurand, base, metric_sys ),
( rootid, 'giga ampere',  'GA', measurand, base, metric_sys ),
( rootid, 'mega ampere',  'MA', measurand, base, metric_sys ),
( rootid, 'kilo ampere',  'kA', measurand, base, metric_sys ),
( rootid, 'hekto ampere', 'hA', measurand, base, metric_sys ),
( rootid, 'deka ampere', 'daA', measurand, base, metric_sys ),
( rootid, 'deci ampere',  'dA', measurand, base, metric_sys ),
( rootid, 'centi ampere', 'cA', measurand, base, metric_sys ),
( rootid, 'milli ampere', 'mA', measurand, base, metric_sys ),
( rootid, 'micro ampere', 'µA', measurand, base, metric_sys ),
( rootid, 'nano ampere',  'nA', measurand, base, metric_sys ),
( rootid, 'pico ampere',  'pA', measurand, base, metric_sys ),
( rootid, 'femto ampere', 'fA', measurand, base, metric_sys );


insert into measurands (name, description, dimension_symbol )
values('Length', 'In geometric measurements, length is the most extended dimension of an object', 'L' )
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, description ) values
( rootid, 'metre', 'm', mes_L, 'The meter is the length of the path travelled by light in vacuum during a time interval of 1/299 792 458 of a second.')
returning uid into base;

insert into units (owner, name, symbol, measurand_id, base_unit, metric_system ) values
( rootid, 'terametre', 'Tm',  measurand, base, metric_sys ),
( rootid, 'gigametre', 'Gm',  measurand, base, metric_sys ),
( rootid, 'megametre', 'Mm',  measurand, base, metric_sys ),
( rootid, 'kilometre', 'km',  measurand, base, metric_sys ),
( rootid, 'hektometre', 'hm', measurand, base, metric_sys ),
( rootid, 'dekametre', 'dam', measurand, base, metric_sys ),
( rootid, 'decimetre', 'dm',  measurand, base, metric_sys ),
( rootid, 'centimetre', 'cm', measurand, base, metric_sys ),
( rootid, 'millimetre', 'mm', measurand, base, metric_sys ),
( rootid, 'micrometre', 'µm', measurand, base, metric_sys ),
( rootid, 'nanometre', 'nm',  measurand, base, metric_sys ),
( rootid, 'picometre', 'pm',  measurand, base, metric_sys ),
( rootid, 'femtometre', 'fm', measurand, base, metric_sys );

--insert into measurands (name, description, dimension_symbol ) values('Mass', '', 'M' ) returning id into mes_M;
--insert into measurands (name, description, dimension_symbol ) values('Time', '', 'T' ) returning id into mes_T;
--insert into measurands (name, description, dimension_symbol ) values('Thermodynamic temperature', '', 'Θ')returning id into mes_o;
--insert into measurands (name, description, dimension_symbol ) values('Amount of substance', '', 'N')returning id into mes_N;
--insert into measurands (name, description, dimension_symbol ) values('Luminous intensity', '', 'J')returning id into mes_J;

--insert into units (owner, name, symbol, measurand_id, description ) values
-- ( rootid, 'kilogram', 'kg', mes_M, 'The kilogram is the unit of mass; it is equal to the mass of the international prototype of the kilogram - Pavillon de Breteuil (Sèvres).' ),
-- ( rootid, 'second', 's', mes_T, 'The second is the duration of 9 192 631 770 periods of the radiation corresponding to the transition between the two hyperfine levels of the ground state of the cesium 133 atom.' ),
-- ( rootid, 'kelvin', 'K', mes_o, 'The kelvin, unit of thermodynamic temperature, is the fraction 1/273.16 of the thermodynamic temperature of the triple point of water.'),
-- ( rootid, 'mole', 'mol', mes_N, '1. The mole is the amount of substance of a system which contains as many elementary entities as there are atoms in 0.012 kilogram of carbon 12; its symbol is "mol." 2. When the mole is used, the elementary entities must be specified and may be atoms, molecules, ions, electrons, other particles, or specified groups of such particles.'),
-- ( rootid, 'candela', 'cd', mes_J, 'The candela is the luminous intensity, in a given direction, of a source that emits monochromatic radiation of frequency 540 x 1012 hertz and that has a radiant intensity in that direction of 1/683 watt per steradian.');


END $$;
rollback transaction;
