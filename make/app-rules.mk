
all: install

clean:
	rm -f $(APP) $(DESTDIR)/$(APP)

$(APP): $(APP).c 
	$(CC) -g3 -o $@ $<

install: $(APP)
	cp $< $(DESTDIR)

