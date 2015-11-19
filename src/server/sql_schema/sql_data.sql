DO
$$
DECLARE rootid int;
DECLARE measurand int;
DECLARE base int;
DECLARE metric_sys int;
DECLARE derived_SI_sys int;
DECLARE unit_id int;
DECLARE text_unit_id int;
BEGIN

select uid from users where name = 'ROOT' limit 1 into rootid;

insert into metric_systems(name) values ('SI')          returning id into metric_sys;
insert into metric_systems(name) values ('SI derived')  returning id into derived_SI_sys;

insert into units (owner, name, symbol) values ( rootid, 'Text',  'TXT' ) returning uid into text_unit_id;

insert into parameters (owner, name, symbol, unit, description, ptype) values
( rootid, 'Typ Rezystora', '', text_unit_id, '', 'pointed' ),
( rootid, 'Producent', '', text_unit_id, '', 'pointed' ) ;

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
( rootid, 'milliampere', 'mA', measurand, base, metric_sys ),
( rootid, 'microampere', 'µA', measurand, base, metric_sys ),
( rootid, 'nanoampere',  'nA', measurand, base, metric_sys ),
( rootid, 'picoampere',  'pA', measurand, base, metric_sys ),
( rootid, 'femtoampere', 'fA', measurand, base, metric_sys );

insert into parameters (owner, name, symbol, unit, description, ptype) values
( rootid, 'Prąd Znamionowy', '', base, '', 'stored' ),
( rootid, 'Zdolność wyłączania', '', base, '', 'stored' ),
( rootid, 'Prąd ładowania maks.', '', base, '', 'stored' ),
( rootid, 'Prąd zwarciowy', '', base, '', 'stored' ),
( rootid, 'Prąd znamionowy', '', base, '', 'stored' ),
( rootid, 'Prąd zasilania DC', '', base, '', 'stored' );

insert into measurands (name, description, dimension_symbol )
values('electrical resistance', '', 'R')
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, metric_system ) values
( rootid, 'ohm', 'Ω', measurand, derived_SI_sys) returning uid into base;

insert into units (owner, name, symbol, measurand_id, base_unit, metric_system ) values
( rootid, 'teraohm',  'TΩ', measurand, base, derived_SI_sys ),
( rootid, 'gigaohm',  'GΩ', measurand, base, derived_SI_sys ),
( rootid, 'megaohm',  'MΩ', measurand, base, derived_SI_sys ),
( rootid, 'kiloohm',  'kΩ', measurand, base, derived_SI_sys ),
( rootid, 'milliohm', 'mΩ', measurand, base, derived_SI_sys ),
( rootid, 'microohm', 'µΩ', measurand, base, derived_SI_sys ),
( rootid, 'nanoohm',  'nΩ', measurand, base, derived_SI_sys ),
( rootid, 'picoohm',  'pΩ', measurand, base, derived_SI_sys ),
( rootid, 'femtoohm', 'fΩ', measurand, base, derived_SI_sys );

insert into measurands (name, description, dimension_symbol )
values('Electric power', 'Electric power is the rate at which electrical energy is transferred by an electric circuit. The SI unit of power is the watt, one joule per second', 'P')
returning id into measurand;

insert into units (owner, name, symbol, measurand_id, metric_system ) values
( rootid, 'watt', 'W', measurand, derived_SI_sys) returning uid into base;

insert into units (owner, name, symbol, measurand_id, base_unit, metric_system ) values
( rootid, 'terawatt',  'TW', measurand, base, derived_SI_sys ),
( rootid, 'gigawatt',  'GW', measurand, base, derived_SI_sys ),
( rootid, 'megawatt',  'MW', measurand, base, derived_SI_sys ),
( rootid, 'kilowatt',  'kW', measurand, base, derived_SI_sys ),
( rootid, 'milliwatt', 'mW', measurand, base, derived_SI_sys ),
( rootid, 'microwatt', 'µW', measurand, base, derived_SI_sys ),
( rootid, 'nanowatt',  'nW', measurand, base, derived_SI_sys ),
( rootid, 'picowatt',  'pW', measurand, base, derived_SI_sys ),
( rootid, 'femtowatt', 'fW', measurand, base, derived_SI_sys );

insert into parameters (owner, name, symbol, unit, description, ptype) values
( rootid, 'Moc', 'W', base, '', 'stored' );

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
