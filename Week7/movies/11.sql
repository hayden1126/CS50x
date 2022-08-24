SELECT movies.title
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
INNER JOIN stars
ON stars.movie_id = ratings.movie_id
WHERE stars.person_id = (SELECT id FROM people WHERE name = "Chadwick Boseman") ORDER BY rating DESC LIMIT 5;