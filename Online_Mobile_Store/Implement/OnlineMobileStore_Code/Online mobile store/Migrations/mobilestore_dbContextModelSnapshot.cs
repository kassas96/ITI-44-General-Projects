﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using Online_mobile_store.Models;

#nullable disable

namespace Online_mobile_store.Migrations
{
    [DbContext(typeof(mobilestore_dbContext))]
    partial class mobilestore_dbContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "8.0.4")
                .HasAnnotation("Relational:MaxIdentifierLength", 128);

            SqlServerModelBuilderExtensions.UseIdentityColumns(modelBuilder);

            modelBuilder.Entity("Online_mobile_store.Models.Product", b =>
                {
                    b.Property<int>("prod_id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("prod_id"));

                    b.Property<string>("image")
                        .HasMaxLength(50)
                        .IsUnicode(false)
                        .HasColumnType("varchar(50)");

                    b.Property<decimal?>("price")
                        .HasColumnType("money");

                    b.Property<string>("prod_name")
                        .HasMaxLength(50)
                        .IsUnicode(false)
                        .HasColumnType("varchar(50)");

                    b.Property<int?>("quantity")
                        .HasColumnType("int");

                    b.Property<int?>("sellerid")
                        .HasColumnType("int");

                    b.Property<string>("type")
                        .HasMaxLength(50)
                        .IsUnicode(false)
                        .HasColumnType("varchar(50)");

                    b.HasKey("prod_id");

                    b.HasIndex("sellerid");

                    b.ToTable("Products");
                });

            modelBuilder.Entity("Online_mobile_store.Models.User", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<string>("Email")
                        .IsRequired()
                        .HasMaxLength(50)
                        .IsUnicode(false)
                        .HasColumnType("varchar(50)");

                    b.Property<int>("Gender")
                        .HasMaxLength(20)
                        .IsUnicode(false)
                        .HasColumnType("int");

                    b.Property<string>("Password")
                        .IsRequired()
                        .HasMaxLength(50)
                        .IsUnicode(false)
                        .HasColumnType("varchar(50)");

                    b.Property<string>("Role")
                        .HasMaxLength(20)
                        .IsUnicode(false)
                        .HasColumnType("varchar(20)");

                    b.Property<string>("UserName")
                        .HasMaxLength(50)
                        .IsUnicode(false)
                        .HasColumnType("varchar(50)");

                    b.HasKey("ID");

                    b.ToTable("Users");
                });

            modelBuilder.Entity("Online_mobile_store.Models.Users_Product", b =>
                {
                    b.Property<int>("user_id")
                        .HasColumnType("int");

                    b.Property<int>("prod_id")
                        .HasColumnType("int");

                    b.Property<DateOnly?>("date")
                        .HasColumnType("date");

                    b.Property<int?>("selected_quantity")
                        .HasColumnType("int");

                    b.Property<string>("status")
                        .HasMaxLength(20)
                        .IsUnicode(false)
                        .HasColumnType("varchar(20)");

                    b.HasKey("user_id", "prod_id")
                        .HasName("PK_Selected_Products");

                    b.HasIndex("prod_id");

                    b.ToTable("Users_Products");
                });

            modelBuilder.Entity("Online_mobile_store.Models.Product", b =>
                {
                    b.HasOne("Online_mobile_store.Models.User", "seller")
                        .WithMany("Products")
                        .HasForeignKey("sellerid")
                        .HasConstraintName("FK_Products_Users");

                    b.Navigation("seller");
                });

            modelBuilder.Entity("Online_mobile_store.Models.Users_Product", b =>
                {
                    b.HasOne("Online_mobile_store.Models.Product", "prod")
                        .WithMany("Users_Products")
                        .HasForeignKey("prod_id")
                        .IsRequired()
                        .HasConstraintName("FK_Users_Products_Products");

                    b.HasOne("Online_mobile_store.Models.User", "user")
                        .WithMany("Users_Products")
                        .HasForeignKey("user_id")
                        .IsRequired()
                        .HasConstraintName("FK_Users_Products_Users");

                    b.Navigation("prod");

                    b.Navigation("user");
                });

            modelBuilder.Entity("Online_mobile_store.Models.Product", b =>
                {
                    b.Navigation("Users_Products");
                });

            modelBuilder.Entity("Online_mobile_store.Models.User", b =>
                {
                    b.Navigation("Products");

                    b.Navigation("Users_Products");
                });
#pragma warning restore 612, 618
        }
    }
}
