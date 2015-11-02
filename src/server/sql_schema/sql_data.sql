DO
$$
DECLARE rootid int;
DECLARE measurand int;
DECLARE base int;
DECLARE metric_sys int;
DECLARE unit_id int;

BEGIN

select uid from users where name = 'ROOT' limit 1 into rootid;

insert into metric_systems(name)
values ('SI')
returning id into metric_sys;

insert into measurands (name, description, dimension_symbol )
values('Electric current', '', 'I')
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, description, metric_system ) values
( rootid, 'ampere', 'A', measurand, 'The ampere is that constant current which, if maintained in two straight parallel conductors of infinite length, of negligible circular cross-section, and placed 1 meter apart in vacuum, would produce between these conductors a force equal to 2 x 10-7 newton per meter of length.', metric_sys)
returning uid into base;

insert into units (owner, name, symbol, measurand_id, base_unit, metric_system ) values
( rootid, 'teraampere',  'TA', measurand, base, metric_sys ),
( rootid, 'gigaampere',  'GA', measurand, base, metric_sys ),
( rootid, 'megaampere',  'MA', measurand, base, metric_sys ),
( rootid, 'kiloampere',  'kA', measurand, base, metric_sys ),
( rootid, 'hektoampere', 'hA', measurand, base, metric_sys ),
( rootid, 'dekaampere', 'daA', measurand, base, metric_sys ),
( rootid, 'deciampere',  'dA', measurand, base, metric_sys ),
( rootid, 'centiampere', 'cA', measurand, base, metric_sys ),
( rootid, 'milliampere', 'mA', measurand, base, metric_sys ),
( rootid, 'microampere', 'µA', measurand, base, metric_sys ),
( rootid, 'nanoampere',  'nA', measurand, base, metric_sys ),
( rootid, 'picoampere',  'pA', measurand, base, metric_sys ),
( rootid, 'femtoampere', 'fA', measurand, base, metric_sys );

insert into measurands (name, description, dimension_symbol )
values('electrical resistance', '', 'R')
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, metric_system ) values
( rootid, 'ohm', 'Ω', measurand, metric_sys) returning uid into unit_id;

--CREATE TABLE parameters (
--    symbol VARCHAR(20),
--    unit INTEGER REFERENCES units(uid),
--    description TEXT CHECK(length(description) < 100000),
--    ptype parameter_type default('stored'),
--    CONSTRAINT parameters_pkey PRIMARY KEY (uid),
--    CONSTRAINT parametereowner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE,
--    CONSTRAINT parameters_unique UNIQUE(name, symbol)
--) INHERITS (stat);

insert into parameters (owner, name, symbol, unit, description, ptype) values
( rootid, 'Rezystancja', 'R', unit_id, '', 'stored' );

insert into measurands (name, description, dimension_symbol )
values('Length', 'In geometric measurements, length is the most extended dimension of an object', 'L' )
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, description, metric_system ) values
( rootid, 'metre', 'm', measurand, 'The meter is the length of the path travelled by light in vacuum during a time interval of 1/299 792 458 of a second.', metric_sys)
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

insert into measurands (name, description, dimension_symbol )
values('Mass', 'In physics, mass is a property of a physical body which determines the strength of its mutual gravitational attraction to other bodies, its resistance to being accelerated by a force, and in the theory of relativity gives the mass–energy content of a system', 'M' )
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, description, metric_system  ) values
( rootid, 'kilogram', 'kg', measurand, 'The kilogram is the unit of mass; it is equal to the mass of the international prototype of the kilogram - Pavillon de Breteuil (Sèvres).', metric_sys )
returning uid into base;

insert into units (owner, name, symbol, measurand_id, base_unit, metric_system ) values
( rootid, 'teragram', 'Tg',  measurand, base, metric_sys ),
( rootid, 'gigagram', 'Gg',  measurand, base, metric_sys ),
( rootid, 'megagram', 'Mg',  measurand, base, metric_sys ),
( rootid, 'hektogram', 'hg', measurand, base, metric_sys ),
( rootid, 'decagram', 'dag', measurand, base, metric_sys ),
( rootid, 'decigram', 'dg',  measurand, base, metric_sys ),
( rootid, 'centigram', 'cg', measurand, base, metric_sys ),
( rootid, 'milligram', 'mg', measurand, base, metric_sys ),
( rootid, 'microgram', 'µg', measurand, base, metric_sys ),
( rootid, 'nanogram', 'ng',  measurand, base, metric_sys ),
( rootid, 'picogram', 'pg',  measurand, base, metric_sys ),
( rootid, 'femtogram', 'fg', measurand, base, metric_sys );

insert into measurands (name, description, dimension_symbol )
values('Time', 'Time is a measure in which events can be ordered from the past through the present into the future, and also the measure of durations of events and the intervals between them.', 'T' )
returning id into measurand;

insert into measurands (name, description, dimension_symbol )
values('Thermodynamic temperature', '', 'Θ' )
returning id into measurand;

insert into measurands (name, description, dimension_symbol )
values('Amount of substance', '', 'N')
returning id into measurand;

insert into measurands (name, description, dimension_symbol )
values('Luminous intensity', '', 'J')
returning id into measurand;

--insert into units (owner, name, symbol, measurand_id, description ) values
-- ( rootid, 'second', 's', mes_T, 'The second is the duration of 9 192 631 770 periods of the radiation corresponding to the transition between the two hyperfine levels of the ground state of the cesium 133 atom.' ),
-- ( rootid, 'kelvin', 'K', mes_o, 'The kelvin, unit of thermodynamic temperature, is the fraction 1/273.16 of the thermodynamic temperature of the triple point of water.'),
-- ( rootid, 'mole', 'mol', mes_N, '1. The mole is the amount of substance of a system which contains as many elementary entities as there are atoms in 0.012 kilogram of carbon 12; its symbol is "mol." 2. When the mole is used, the elementary entities must be specified and may be atoms, molecules, ions, electrons, other particles, or specified groups of such particles.'),
-- ( rootid, 'candela', 'cd', mes_J, 'The candela is the luminous intensity, in a given direction, of a source that emits monochromatic radiation of frequency 540 x 1012 hertz and that has a radiant intensity in that direction of 1/683 watt per steradian.');


END $$;
