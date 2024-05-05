delete from public.epix_posts as P
using public.epix_hashtags as H , public.epix_accounts as E, public.people as Pe
where H.id = P.hashtag_id
and P.author_id = E.id
and E.person_id = Pe.id
and H.name like 'EndSurveillance'
returning first_name,
    last_name,
    username,
    P.body as post_content
    ;
