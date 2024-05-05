update public.epix_posts
set downvotes = (select upvotes * (select avg(cast(downvotes as float)/cast(upvotes as float))
                                            from public.epix_posts
                                                where author_id = 933
                                            and id != 139)
                    from public.epix_posts
                        where id = 139)
where id = 139;
