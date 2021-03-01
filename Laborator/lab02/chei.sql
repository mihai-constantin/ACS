-- Primary Keys

ALTER TABLE departamente ADD CONSTRAINT pk_departamente PRIMARY KEY (id_departament);
ALTER TABLE grila_salariu ADD CONSTRAINT pk_grila PRIMARY KEY (grad);
ALTER TABLE angajati ADD CONSTRAINT pk_angajati PRIMARY KEY (id_angajat);

-- Foreign Keys
ALTER TABLE angajati ADD CONSTRAINT fk_ang__dep FOREIGN KEY (id_departament) REFERENCES departamente(id_departament);

ALTER TABLE angajati ADD CONSTRAINT fk_ang__ang FOREIGN KEY (id_sef) REFERENCES angajati(id_angajat);

-- Unique

ALTER TABLE departamente ADD CONSTRAINT uq_denumire UNIQUE (denumire_departament);

ALTER TABLE angajati ADD CONSTRAINT uq_nume UNIQUE (nume, prenume);

DROP TABLE departamente;
DROP TABLE angajati;
DROP TABLE grila_salariu;