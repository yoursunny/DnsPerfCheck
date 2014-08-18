CREATE TABLE domains (
  ID int NOT NULL AUTO_INCREMENT,
  name varchar(200) NOT NULL,
  enabled tinyint NOT NULL,
  PRIMARY KEY (ID)
);

CREATE UNIQUE INDEX domains_name
USING BTREE
ON domains (
  name ASC
);

INSERT INTO domains(name,enabled)
VALUES ('example.com',   0),
       ('example.net',   0),
       ('google.com',    1),
       ('facebook.com',  1),
       ('youtube.com',   1),
       ('yahoo.com',     1),
       ('live.com',      1),
       ('wikipedia.org', 1),
       ('baidu.com',     1),
       ('blogger.com',   1),
       ('msn.com',       1),
       ('qq.com',        1);

CREATE TABLE probelogs (
  ID bigint NOT NULL AUTO_INCREMENT,
  dt timestamp NOT NULL,
  domain int NOT NULL,
  query_time int NOT NULL,
  PRIMARY KEY (ID),
  FOREIGN KEY fk_domain(domain) REFERENCES domains(ID)
);

CREATE INDEX probelog_domaintime
USING BTREE
ON probelogs (
  domain ASC,
  timestamp ASC
);

CREATE VIEW report AS
  SELECT
    domains.name domain_name,
    AVG(query_time) avg_query_time,
    STDDEV(query_time) stddev_query_time,
    COUNT(*) n_queries,
    MIN(dt) first_timestamp,
    MAX(dt) last_timestamp
  FROM probelogs
  INNER JOIN domains ON probelogs.domain = domains.ID
  GROUP BY domains.ID;

