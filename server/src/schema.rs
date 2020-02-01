table! {
    scrap (id) {
        id -> Integer,
        site_name -> Varchar,
        description -> Varchar,
        headers -> Text,
        body -> Text,
        created_at -> Nullable<Timestamp>,
        updated_at -> Nullable<Timestamp>,
    }
}
