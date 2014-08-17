CREATE TABLE probelog (
  ID bigint NOT NULL AUTO_INCREMENT,
  dt timestamp NOT NULL,
  domain varchar(200) NOT NULL,
  query_time int NOT NULL,
  PRIMARY KEY (ID)
);

CREATE INDEX probelog_domaintime
USING BTREE
ON probelog (
  domain ASC,
  timestamp ASC
);

CREATE VIEW report AS
  SELECT
    domain,
    AVG(query_time) avg_query_time,
    STDDEV(query_time) stddev_query_time,
    COUNT(*) n_queries,
    MIN(dt) first_timestamp,
    MAX(dt) last_timestamp
  FROM probelog
  GROUP BY domain;
