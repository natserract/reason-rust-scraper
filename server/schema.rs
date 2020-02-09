table! {
    scrap (id) {
        id -> Integer,
        site_name -> Varchar,
        description -> Varchar,
        headers -> Text,
        ip_address -> Varchar,
        html_code -> Text,
        all_links -> Text,
        images -> Text,
        created_at -> Nullable<Timestamp>,
        updated_at -> Nullable<Timestamp>,
    }
}
