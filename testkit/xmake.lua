target("testkit")
    set_kind("static")
    add_files("*.c")
    add_includedirs(".", {public = true})