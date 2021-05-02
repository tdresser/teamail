#define TO_JSON(CLASSNAME,                                               \
                INSTANCENAME) /* NOLINT(readability-identifier-naming)*/ \
  void to_json(json& j, const CLASSNAME&(INSTANCENAME)) {                \
    (INSTANCENAME).toJson(j);                                            \
  };

#define FROM_JSON(CLASSNAME, INSTANCENAME)                                 \
  void from_json(                                                          \
      const json& j,                                                       \
      CLASSNAME&(INSTANCENAME)) { /* NOLINT(readability-identifier-naming, \
                                     bugprone-macro-parenthesis)*/         \
    (INSTANCENAME).fromJson(j);                                            \
  };

#define JSON_SERIALIZE_ENUM NLOHMANN_JSON_SERIALIZE_ENUM
