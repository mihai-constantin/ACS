package com.luxoft.bankapp.annotations;

public abstract class ActiveRecord {
    public String getById(int id) {
        ActiveRecordEntity activeRecordEntity = this.getClass().getAnnotation(ActiveRecordEntity.class);
        String tableName = activeRecordEntity.tableName();
        String columnKeyName = activeRecordEntity.columnKeyName();
        return "SELECT * FROM " + tableName + " WHERE " + columnKeyName + "=" + id;
    }

    public String getAll() {
        ActiveRecordEntity activeRecordEntity = this.getClass().getAnnotation(ActiveRecordEntity.class);
        String tableName = activeRecordEntity.tableName();
        return "SELECT * FROM " + tableName;
    }
}
